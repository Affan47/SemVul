vxge_hw_mgmt_reg_write(struct __vxge_hw_device *hldev,
		      enum vxge_hw_mgmt_reg_type type,
		      u32 index, u32 offset, u64 value)
{
	enum vxge_hw_status status = VXGE_HW_OK;

	if ((hldev == NULL) || (hldev->magic != VXGE_HW_DEVICE_MAGIC)) {
		status = VXGE_HW_ERR_INVALID_DEVICE;
		goto exit;
	}

	switch (type) {
	case vxge_hw_mgmt_reg_type_legacy:
		if (offset > sizeof(struct vxge_hw_legacy_reg) - 8) {
			status = VXGE_HW_ERR_INVALID_OFFSET;
			break;
		}
		writeq(value, (void __iomem *)hldev->legacy_reg + offset);
		break;
	case vxge_hw_mgmt_reg_type_toc:
		if (offset > sizeof(struct vxge_hw_toc_reg) - 8) {
			status = VXGE_HW_ERR_INVALID_OFFSET;
			break;
		}
		writeq(value, (void __iomem *)hldev->toc_reg + offset);
		break;
	case vxge_hw_mgmt_reg_type_common:
		if (offset > sizeof(struct vxge_hw_common_reg) - 8) {
			status = VXGE_HW_ERR_INVALID_OFFSET;
			break;
		}
		writeq(value, (void __iomem *)hldev->common_reg + offset);
		break;
	case vxge_hw_mgmt_reg_type_mrpcim:
		if (!(hldev->access_rights &
			VXGE_HW_DEVICE_ACCESS_RIGHT_MRPCIM)) {
			status = VXGE_HW_ERR_PRIVILAGED_OPEARATION;
			break;
		}
		if (offset > sizeof(struct vxge_hw_mrpcim_reg) - 8) {
			status = VXGE_HW_ERR_INVALID_OFFSET;
			break;
		}
		writeq(value, (void __iomem *)hldev->mrpcim_reg + offset);
		break;
	case vxge_hw_mgmt_reg_type_srpcim:
		if (!(hldev->access_rights &
			VXGE_HW_DEVICE_ACCESS_RIGHT_SRPCIM)) {
			status = VXGE_HW_ERR_PRIVILAGED_OPEARATION;
			break;
		}
		if (index > VXGE_HW_TITAN_SRPCIM_REG_SPACES - 1) {
			status = VXGE_HW_ERR_INVALID_INDEX;
			break;
		}
		if (offset > sizeof(struct vxge_hw_srpcim_reg) - 8) {
			status = VXGE_HW_ERR_INVALID_OFFSET;
			break;
		}
		writeq(value, (void __iomem *)hldev->srpcim_reg[index] +
			offset);

		break;
	case vxge_hw_mgmt_reg_type_vpmgmt:
		if ((index > VXGE_HW_TITAN_VPMGMT_REG_SPACES - 1) ||
			(!(hldev->vpath_assignments & vxge_mBIT(index)))) {
			status = VXGE_HW_ERR_INVALID_INDEX;
			break;
		}
		if (offset > sizeof(struct vxge_hw_vpmgmt_reg) - 8) {
			status = VXGE_HW_ERR_INVALID_OFFSET;
			break;
		}
		writeq(value, (void __iomem *)hldev->vpmgmt_reg[index] +
			offset);
		break;
	case vxge_hw_mgmt_reg_type_vpath:
		if ((index > VXGE_HW_TITAN_VPATH_REG_SPACES-1) ||
			(!(hldev->vpath_assignments & vxge_mBIT(index)))) {
			status = VXGE_HW_ERR_INVALID_INDEX;
			break;
		}
		if (offset > sizeof(struct vxge_hw_vpath_reg) - 8) {
			status = VXGE_HW_ERR_INVALID_OFFSET;
			break;
		}
		writeq(value, (void __iomem *)hldev->vpath_reg[index] +
			offset);
		break;
	default:
		status = VXGE_HW_ERR_INVALID_TYPE;
		break;
	}
exit:
	return status;
}
