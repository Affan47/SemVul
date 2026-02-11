kfd_dbgdev_init(struct kfd_dbgdev *pdbgdev, struct kfd_dev *pdev,
			enum DBGDEV_TYPE type)
{
	BUG_ON(!pdbgdev || !pdev);

	pdbgdev->dev = pdev;
	pdbgdev->kq = NULL;
	pdbgdev->type = type;
	pdbgdev->pqm = NULL;

	switch (type) {
	case DBGDEV_TYPE_NODIQ:
		pdbgdev->dbgdev_register = dbgdev_register_nodiq;
		pdbgdev->dbgdev_unregister = dbgdev_unregister_nodiq;
		pdbgdev->dbgdev_wave_control = dbgdev_wave_control_nodiq;
		pdbgdev->dbgdev_address_watch = dbgdev_address_watch_nodiq;
		break;
	case DBGDEV_TYPE_DIQ:
	default:
		pdbgdev->dbgdev_register = dbgdev_register_diq;
		pdbgdev->dbgdev_unregister = dbgdev_unregister_diq;
		pdbgdev->dbgdev_wave_control =  dbgdev_wave_control_diq;
		pdbgdev->dbgdev_address_watch = dbgdev_address_watch_diq;
		break;
	}

}
