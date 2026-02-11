vficon_unselect(ViewFile *vf, IconData *id)
{
	VFICON(vf)->prev_selection = id;

	if (!id || !(id->selected & SELECTION_SELECTED) ) return;

	VFICON(vf)->selection = g_list_remove(VFICON(vf)->selection, id);
	vficon_selection_remove(vf, id, SELECTION_SELECTED, NULL);

	vf_send_update(vf);
}
