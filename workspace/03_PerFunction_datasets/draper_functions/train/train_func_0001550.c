i40e_aq_str(struct i40e_hw *hw, enum i40e_admin_queue_err aq_err)
{
	switch (aq_err) {
	case I40E_AQ_RC_OK:
		return "OK";
	case I40E_AQ_RC_EPERM:
		return "I40E_AQ_RC_EPERM";
	case I40E_AQ_RC_ENOENT:
		return "I40E_AQ_RC_ENOENT";
	case I40E_AQ_RC_ESRCH:
		return "I40E_AQ_RC_ESRCH";
	case I40E_AQ_RC_EINTR:
		return "I40E_AQ_RC_EINTR";
	case I40E_AQ_RC_EIO:
		return "I40E_AQ_RC_EIO";
	case I40E_AQ_RC_ENXIO:
		return "I40E_AQ_RC_ENXIO";
	case I40E_AQ_RC_E2BIG:
		return "I40E_AQ_RC_E2BIG";
	case I40E_AQ_RC_EAGAIN:
		return "I40E_AQ_RC_EAGAIN";
	case I40E_AQ_RC_ENOMEM:
		return "I40E_AQ_RC_ENOMEM";
	case I40E_AQ_RC_EACCES:
		return "I40E_AQ_RC_EACCES";
	case I40E_AQ_RC_EFAULT:
		return "I40E_AQ_RC_EFAULT";
	case I40E_AQ_RC_EBUSY:
		return "I40E_AQ_RC_EBUSY";
	case I40E_AQ_RC_EEXIST:
		return "I40E_AQ_RC_EEXIST";
	case I40E_AQ_RC_EINVAL:
		return "I40E_AQ_RC_EINVAL";
	case I40E_AQ_RC_ENOTTY:
		return "I40E_AQ_RC_ENOTTY";
	case I40E_AQ_RC_ENOSPC:
		return "I40E_AQ_RC_ENOSPC";
	case I40E_AQ_RC_ENOSYS:
		return "I40E_AQ_RC_ENOSYS";
	case I40E_AQ_RC_ERANGE:
		return "I40E_AQ_RC_ERANGE";
	case I40E_AQ_RC_EFLUSHED:
		return "I40E_AQ_RC_EFLUSHED";
	case I40E_AQ_RC_BAD_ADDR:
		return "I40E_AQ_RC_BAD_ADDR";
	case I40E_AQ_RC_EMODE:
		return "I40E_AQ_RC_EMODE";
	case I40E_AQ_RC_EFBIG:
		return "I40E_AQ_RC_EFBIG";
	}

	snprintf(hw->err_str, sizeof(hw->err_str), "%d", aq_err);
	return hw->err_str;
}
