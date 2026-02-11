sci_controller_sdma_completion(struct isci_host *ihost, u32 ent)
{
	u32 index;
	struct isci_request *ireq;
	struct isci_remote_device *idev;

	index = SCU_GET_COMPLETION_INDEX(ent);

	switch (scu_get_command_request_type(ent)) {
	case SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_TC:
	case SCU_CONTEXT_COMMAND_REQUEST_TYPE_DUMP_TC:
		ireq = ihost->reqs[index];
		dev_warn(&ihost->pdev->dev, "%s: %x for io request %p\n",
			 __func__, ent, ireq);


		break;
	case SCU_CONTEXT_COMMAND_REQUEST_TYPE_DUMP_RNC:
	case SCU_CONTEXT_COMMAND_REQUEST_TYPE_OTHER_RNC:
	case SCU_CONTEXT_COMMAND_REQUEST_TYPE_POST_RNC:
		idev = ihost->device_table[index];
		dev_warn(&ihost->pdev->dev, "%s: %x for device %p\n",
			 __func__, ent, idev);


		break;
	default:
		dev_warn(&ihost->pdev->dev, "%s: unknown completion type %x\n",
			 __func__, ent);
		break;
	}
}
