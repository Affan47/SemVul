mono_bitset_print (MonoBitSet *set)
{
	int i;
	gboolean first = TRUE;

	printf ("{");
	for (i = 0; i < mono_bitset_size (set); i++) {

		if (mono_bitset_test (set, i)) {
			if (!first)
				printf (", ");
			printf ("%d", i);
			first = FALSE;
		}
	}
	printf ("}\n");
}
