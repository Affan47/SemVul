cvs_patch_free (cvs_patch *patch)

{
    cvs_patch	*v;

    while ((v = patch)) {
	patch = v->next;
	free (v->text);
	free (v);
    }
}
