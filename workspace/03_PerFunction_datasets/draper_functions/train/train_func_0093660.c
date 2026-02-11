cb_File_Save (wxCommandEvent &event)
{
	FancyFileSelection fs (this, _("Save File"), wxSAVE, true);

	if (fs.ShowModal () == wxID_CANCEL)
		return;


	if (graph->get_tag ("creator").IsEmpty ())
		graph->set_tag ("creator", wxT("GraphThing " GT_VERSION));

	Exporter *exp = Exporter::make (fs.GetFileType (), fs.GetFileName ());
	bool labels = view_Labels->IsChecked ();
	bool weights = view_Weights->IsChecked ();
	exp->output (graph, labels, weights);
	delete exp;
}
