cml_crystal_start (GsfXMLIn *xin, G_GNUC_UNUSED xmlChar const **attrs)
{
	CMLReadState *state = (CMLReadState *) xin->user_state;
	state->type = ContentTypeCrystal;
	state->data = new SpaceGroup ();

	state->doc->SetScale (1.);
}
