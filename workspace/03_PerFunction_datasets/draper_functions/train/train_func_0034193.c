ia_que_tx (IADEV *iadev) {
   struct sk_buff *skb;
   int num_desc;
   struct atm_vcc *vcc;
   num_desc = ia_avail_descs(iadev);

   while (num_desc && (skb = skb_dequeue(&iadev->tx_backlog))) {
      if (!(vcc = ATM_SKB(skb)->vcc)) {
         dev_kfree_skb_any(skb);
         printk("ia_que_tx: Null vcc\n");
         break;
      }
      if (!test_bit(ATM_VF_READY,&vcc->flags)) {
         dev_kfree_skb_any(skb);
         printk("Free the SKB on closed vci %d \n", vcc->vci);
         break;
      }
      if (ia_pkt_tx (vcc, skb)) {
         skb_queue_head(&iadev->tx_backlog, skb);
      }
      num_desc--;
   }
   return 0;
}
