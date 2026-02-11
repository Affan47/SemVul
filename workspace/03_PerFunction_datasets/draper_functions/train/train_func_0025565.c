SaveEmoticons()
{
	FILE* fo = fopen( AppConfig.GetConfigPath( emoticon_file_name ).c_str() , "w" );
	if( fo )
	{
		GtkTreeModel* model = m_List->GetTreeModel();
		gtk_tree_model_foreach( model, (GtkTreeModelForeachFunc)CEmoticonDlg::SaveEmoticon, fo );
		fclose(fo);
	}
}
