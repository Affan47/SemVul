cml_crystal_end (GsfXMLIn *xin, G_GNUC_UNUSED GsfXMLBlob *blob)
{
	CMLReadState *state = (CMLReadState *) xin->user_state;
	SpaceGroup *group = static_cast <SpaceGroup *> (state->data);
	SpaceGroup const *found = SpaceGroup::Find (group);
	if (found != NULL)
		state->doc->SetProperty (GCU_PROP_SPACE_GROUP, found->GetHallName ().c_str ());
	delete group;
	state->data = NULL;
}
