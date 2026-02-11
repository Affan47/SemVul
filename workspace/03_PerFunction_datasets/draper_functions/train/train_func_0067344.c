check_offsets(void)
{

	BUILD_BUG_ON(VIRTIO_PCI_CAP_VNDR !=
		     offsetof(struct virtio_pci_cap, cap_vndr));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_NEXT !=
		     offsetof(struct virtio_pci_cap, cap_next));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_LEN !=
		     offsetof(struct virtio_pci_cap, cap_len));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_CFG_TYPE !=
		     offsetof(struct virtio_pci_cap, cfg_type));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_BAR !=
		     offsetof(struct virtio_pci_cap, bar));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_OFFSET !=
		     offsetof(struct virtio_pci_cap, offset));
	BUILD_BUG_ON(VIRTIO_PCI_CAP_LENGTH !=
		     offsetof(struct virtio_pci_cap, length));
	BUILD_BUG_ON(VIRTIO_PCI_NOTIFY_CAP_MULT !=
		     offsetof(struct virtio_pci_notify_cap,
			      notify_off_multiplier));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_DFSELECT !=
		     offsetof(struct virtio_pci_common_cfg,
			      device_feature_select));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_DF !=
		     offsetof(struct virtio_pci_common_cfg, device_feature));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_GFSELECT !=
		     offsetof(struct virtio_pci_common_cfg,
			      guest_feature_select));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_GF !=
		     offsetof(struct virtio_pci_common_cfg, guest_feature));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_MSIX !=
		     offsetof(struct virtio_pci_common_cfg, msix_config));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_NUMQ !=
		     offsetof(struct virtio_pci_common_cfg, num_queues));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_STATUS !=
		     offsetof(struct virtio_pci_common_cfg, device_status));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_CFGGENERATION !=
		     offsetof(struct virtio_pci_common_cfg, config_generation));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_SELECT !=
		     offsetof(struct virtio_pci_common_cfg, queue_select));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_SIZE !=
		     offsetof(struct virtio_pci_common_cfg, queue_size));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_MSIX !=
		     offsetof(struct virtio_pci_common_cfg, queue_msix_vector));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_ENABLE !=
		     offsetof(struct virtio_pci_common_cfg, queue_enable));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_NOFF !=
		     offsetof(struct virtio_pci_common_cfg, queue_notify_off));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_DESCLO !=
		     offsetof(struct virtio_pci_common_cfg, queue_desc_lo));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_DESCHI !=
		     offsetof(struct virtio_pci_common_cfg, queue_desc_hi));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_AVAILLO !=
		     offsetof(struct virtio_pci_common_cfg, queue_avail_lo));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_AVAILHI !=
		     offsetof(struct virtio_pci_common_cfg, queue_avail_hi));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_USEDLO !=
		     offsetof(struct virtio_pci_common_cfg, queue_used_lo));
	BUILD_BUG_ON(VIRTIO_PCI_COMMON_Q_USEDHI !=
		     offsetof(struct virtio_pci_common_cfg, queue_used_hi));
}
