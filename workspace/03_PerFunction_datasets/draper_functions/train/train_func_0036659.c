bnx2fc_mod_exit(void)
{
	LIST_HEAD(to_be_deleted);
	struct bnx2fc_hba *hba, *next;
	struct fcoe_percpu_s *bg;
	struct task_struct *l2_thread;
	struct sk_buff *skb;
	unsigned int cpu = 0;


	mutex_lock(&bnx2fc_dev_lock);
	list_splice(&adapter_list, &to_be_deleted);
	INIT_LIST_HEAD(&adapter_list);
	adapter_count = 0;
	mutex_unlock(&bnx2fc_dev_lock);


	list_for_each_entry_safe(hba, next, &to_be_deleted, list) {
		list_del_init(&hba->list);
		printk(KERN_ERR PFX "MOD_EXIT:destroy hba = 0x%p\n",
		       hba);
		bnx2fc_ulp_stop(hba);

		if (test_and_clear_bit(BNX2FC_CNIC_REGISTERED,
				       &hba->reg_with_cnic))
			hba->cnic->unregister_device(hba->cnic,
							 CNIC_ULP_FCOE);
		bnx2fc_hba_destroy(hba);
	}
	cnic_unregister_driver(CNIC_ULP_FCOE);


	bg = &bnx2fc_global;
	spin_lock_bh(&bg->fcoe_rx_list.lock);
	l2_thread = bg->thread;
	bg->thread = NULL;
	while ((skb = __skb_dequeue(&bg->fcoe_rx_list)) != NULL)
		kfree_skb(skb);

	spin_unlock_bh(&bg->fcoe_rx_list.lock);

	if (l2_thread)
		kthread_stop(l2_thread);

	cpu_notifier_register_begin();


	for_each_online_cpu(cpu) {
		bnx2fc_percpu_thread_destroy(cpu);
	}

	__unregister_hotcpu_notifier(&bnx2fc_cpu_notifier);

	cpu_notifier_register_done();

	destroy_workqueue(bnx2fc_wq);


	bnx2fc_release_transport();


	fcoe_transport_detach(&bnx2fc_transport);
}
