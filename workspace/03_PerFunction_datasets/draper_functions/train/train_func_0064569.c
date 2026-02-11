proc_show_rebuild_rate(struct seq_file *m, void *v)
{
	adapter_t	*adapter = m->private;
	dma_addr_t	dma_handle;
	caddr_t		inquiry;
	struct pci_dev	*pdev;

	if( make_local_pdev(adapter, &pdev) != 0 )
		return 0;

	if( (inquiry = mega_allocate_inquiry(&dma_handle, pdev)) == NULL )
		goto free_pdev;

	if( mega_adapinq(adapter, dma_handle) != 0 ) {
		seq_puts(m, "Adapter inquiry failed.\n");
		dev_warn(&adapter->dev->dev, "inquiry failed\n");
		goto free_inquiry;
	}

	if( adapter->flag & BOARD_40LD )
		seq_printf(m, "Rebuild Rate: [%d%%]\n",
			   ((mega_inquiry3 *)inquiry)->rebuild_rate);
	else
		seq_printf(m, "Rebuild Rate: [%d%%]\n",
			((mraid_ext_inquiry *)
			 inquiry)->raid_inq.adapter_info.rebuild_rate);

free_inquiry:
	mega_free_inquiry(inquiry, dma_handle, pdev);
free_pdev:
	free_local_pdev(pdev);
	return 0;
}
