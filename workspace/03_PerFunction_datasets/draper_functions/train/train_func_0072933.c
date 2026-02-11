test_slot_equals_hash (Test *test, gconstpointer unused)
{
	GckModule *other_mod;
	GckSlot *other_slot;
	GObject *obj;
	guint hash;

	hash = gck_slot_hash (test->slot);
	g_assert (hash != 0);

	g_assert (gck_slot_equal (test->slot, test->slot));

	other_mod = gck_module_new (gck_module_get_functions (test->module));
	other_slot = g_object_new (GCK_TYPE_SLOT, "module", other_mod, "handle", gck_slot_get_handle (test->slot), NULL);
	g_assert (gck_slot_equal (test->slot, other_slot));
	g_object_unref (other_mod);
	g_object_unref (other_slot);

	obj = g_object_new (G_TYPE_OBJECT, NULL);
	g_assert (!gck_slot_equal (test->slot, obj));
	g_object_unref (obj);

	other_slot = g_object_new (GCK_TYPE_SLOT, "module", test->module, "handle", 8909, NULL);
	g_assert (!gck_slot_equal (test->slot, other_slot));
	g_object_unref (other_slot);
}
