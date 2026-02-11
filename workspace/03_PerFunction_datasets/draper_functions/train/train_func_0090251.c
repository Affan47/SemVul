intel_detect_pch(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct pci_dev *pch = NULL;


	if (INTEL_INFO(dev)->num_pipes == 0) {
		dev_priv->pch_type = PCH_NOP;
		return;
	}


	while ((pch = pci_get_class(PCI_CLASS_BRIDGE_ISA << 8, pch))) {
		if (pch->vendor == PCI_VENDOR_ID_INTEL) {
			unsigned short id = pch->device & INTEL_PCH_DEVICE_ID_MASK;
			dev_priv->pch_id = id;

			if (id == INTEL_PCH_IBX_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_IBX;
				DRM_DEBUG_KMS("Found Ibex Peak PCH\n");
				WARN_ON(!IS_GEN5(dev));
			} else if (id == INTEL_PCH_CPT_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_CPT;
				DRM_DEBUG_KMS("Found CougarPoint PCH\n");
				WARN_ON(!(IS_GEN6(dev) || IS_IVYBRIDGE(dev)));
			} else if (id == INTEL_PCH_PPT_DEVICE_ID_TYPE) {

				dev_priv->pch_type = PCH_CPT;
				DRM_DEBUG_KMS("Found PantherPoint PCH\n");
				WARN_ON(!(IS_GEN6(dev) || IS_IVYBRIDGE(dev)));
			} else if (id == INTEL_PCH_LPT_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_LPT;
				DRM_DEBUG_KMS("Found LynxPoint PCH\n");
				WARN_ON(!IS_HASWELL(dev) && !IS_BROADWELL(dev));
				WARN_ON(IS_HSW_ULT(dev) || IS_BDW_ULT(dev));
			} else if (id == INTEL_PCH_LPT_LP_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_LPT;
				DRM_DEBUG_KMS("Found LynxPoint LP PCH\n");
				WARN_ON(!IS_HASWELL(dev) && !IS_BROADWELL(dev));
				WARN_ON(!IS_HSW_ULT(dev) && !IS_BDW_ULT(dev));
			} else if (id == INTEL_PCH_SPT_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_SPT;
				DRM_DEBUG_KMS("Found SunrisePoint PCH\n");
				WARN_ON(!IS_SKYLAKE(dev) &&
					!IS_KABYLAKE(dev));
			} else if (id == INTEL_PCH_SPT_LP_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_SPT;
				DRM_DEBUG_KMS("Found SunrisePoint LP PCH\n");
				WARN_ON(!IS_SKYLAKE(dev) &&
					!IS_KABYLAKE(dev));
			} else if (id == INTEL_PCH_KBP_DEVICE_ID_TYPE) {
				dev_priv->pch_type = PCH_KBP;
				DRM_DEBUG_KMS("Found KabyPoint PCH\n");
				WARN_ON(!IS_KABYLAKE(dev));
			} else if ((id == INTEL_PCH_P2X_DEVICE_ID_TYPE) ||
				   (id == INTEL_PCH_P3X_DEVICE_ID_TYPE) ||
				   ((id == INTEL_PCH_QEMU_DEVICE_ID_TYPE) &&
				    pch->subsystem_vendor == 0x1af4 &&
				    pch->subsystem_device == 0x1100)) {
				dev_priv->pch_type = intel_virt_detect_pch(dev);
			} else
				continue;

			break;
		}
	}
	if (!pch)
		DRM_DEBUG_KMS("No PCH found.\n");

	pci_dev_put(pch);
}
