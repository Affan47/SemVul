gth_file_list_op_free (GthFileListOp *op)
{
	switch (op->type) {
	case GTH_FILE_LIST_OP_TYPE_SET_FILES:
		_g_object_list_unref (op->file_list);
		break;
	case GTH_FILE_LIST_OP_TYPE_CLEAR_FILES:
		g_free (op->sval);
		break;
	case GTH_FILE_LIST_OP_TYPE_ADD_FILES:
	case GTH_FILE_LIST_OP_TYPE_UPDATE_FILES:
	case GTH_FILE_LIST_OP_TYPE_UPDATE_EMBLEMS:
		_g_object_list_unref (op->file_list);
		break;
	case GTH_FILE_LIST_OP_TYPE_DELETE_FILES:
		_g_object_list_unref (op->files);
		break;
	case GTH_FILE_LIST_OP_TYPE_SET_FILTER:
		g_object_unref (op->filter);
		break;
	case GTH_FILE_LIST_OP_TYPE_RENAME_FILE:
		g_object_unref (op->file);
		g_object_unref (op->file_data);
		break;
	case GTH_FILE_LIST_OP_TYPE_MAKE_FILE_VISIBLE:
		g_object_unref (op->file);
		break;
	case GTH_FILE_LIST_OP_TYPE_RESTORE_STATE:
		g_list_free_full (op->selected, (GDestroyNotify) gtk_tree_path_free);
		break;
	default:
		break;
	}
	g_free (op);
}
