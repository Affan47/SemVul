list_model_row_changed (TestConformSimpleFixture *fixture,
                        gconstpointer             data)
{
  ChangedData test_data = { NULL, NULL, 0, 0 };
  GValue value = { 0, };
  gint i;

  test_data.model = clutter_list_model_new (N_COLUMNS,
                                            G_TYPE_STRING, "Foo",
                                            G_TYPE_INT,    "Bar");
  for (i = 1; i < 10; i++)
    {
      gchar *foo = g_strdup_printf ("String %d", i);

      clutter_model_append (test_data.model,
                            COLUMN_FOO, foo,
                            COLUMN_BAR, i,
                            -1);

      g_free (foo);
    }

  g_signal_connect (test_data.model, "row-changed",
                    G_CALLBACK (on_row_changed),
                    &test_data);

  test_data.row = g_random_int_range (0, 9);
  test_data.iter = clutter_model_get_iter_at_row (test_data.model,
                                                  test_data.row);
  g_assert (CLUTTER_IS_MODEL_ITER (test_data.iter));

  test_data.value_check = 47;

  g_value_init (&value, G_TYPE_INT);
  g_value_set_int (&value, test_data.value_check);

  clutter_model_iter_set_value (test_data.iter, COLUMN_BAR, &value);

  g_value_unset (&value);

  if (g_test_verbose ())
    g_print ("iter.set_value() emissions: %d, expected: 1\n",
             test_data.n_emissions);

  g_assert_cmpint (test_data.n_emissions, ==, 1);

  test_data.n_emissions = 0;
  test_data.value_check = 42;

  clutter_model_iter_set (test_data.iter,
                          COLUMN_FOO, "changed",
                          COLUMN_BAR, test_data.value_check,
                          -1);

  if (g_test_verbose ())
    g_print ("iter.set() emissions: %d, expected: 1\n",
             test_data.n_emissions);

  g_assert_cmpint (test_data.n_emissions, ==, 1);

  g_object_unref (test_data.iter);
  g_object_unref (test_data.model);
}
