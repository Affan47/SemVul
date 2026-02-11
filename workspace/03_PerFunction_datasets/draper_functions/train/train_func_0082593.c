q_resource_requirements(void *context, struct pci_response *resp,
				    int resp_packet_size)
{
	struct q_res_req_compl *completion = context;
	struct pci_q_res_req_response *q_res_req =
		(struct pci_q_res_req_response *)resp;
	int i;

	if (resp->status < 0) {
		dev_err(&completion->hpdev->hbus->hdev->device,
			"query resource requirements failed: %x\n",
			resp->status);
	} else {
		for (i = 0; i < 6; i++) {
			completion->hpdev->probed_bar[i] =
				q_res_req->probed_bar[i];
		}
	}

	complete(&completion->host_event);
}
