Menuscreens_Animate_Insert_To_Steady (void)
{
	int i;
	for (i = 0; i < mstate.incoming.num_layers; i++)
		activelayer(mstate.active.num_layers++) = mstate.incoming.layers[i];
	Cursor_SelectMenu (layergroup_last(mstate.active).screen);
	mstate.incoming.num_layers = 0;
	mstate.outgoing.num_layers = 0;
	mstate.state = mstate_steady;
	mstate.animation = 0;
	Menuscreens_Animate ();
}
