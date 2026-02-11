gtkaspeller_delete(GtkAspeller *gtkaspeller)
{
	cm_return_val_if_fail(gtkaspellcheckers, NULL);

	gtkaspellcheckers->checkers =
		g_slist_remove(gtkaspellcheckers->checkers,
				gtkaspeller);

	debug_print("Aspell: Deleting gtkaspeller %p.\n",
			gtkaspeller);

	gtkaspeller_real_delete(gtkaspeller);

	debug_print("Aspell: number of existing checkers %d\n",
			g_slist_length(gtkaspellcheckers->checkers));

	return gtkaspeller;
}
