PMI_Parse_option(int num_args, char *args[], int *num_parsed,
		     PMI_keyval_t **keyvalp,
		int *size)
{
	int i, n, s, len;
	char *cp, *kp, *vp;
	PMI_keyval_t *temp;

	if (pmi_debug)
		fprintf(stderr, "In: PMI_Parse_option - \n");

	if (num_parsed == NULL)
		return PMI_ERR_INVALID_NUM_PARSED;
	if (keyvalp == NULL)
		return PMI_ERR_INVALID_KEYVALP;
	if (size == NULL)
		return PMI_ERR_INVALID_SIZE;

	i = 0;
	n = 0;
	s = 0;

	cp = args[0];
	temp = (PMI_keyval_t *) malloc(num_args * (sizeof (PMI_keyval_t)));
	if (temp == NULL)
		return PMI_FAIL;

	cp = args[0];
	while (i < num_args) {

		while (*cp == ' ') cp++;
		n++;
		kp = cp;
		while (*cp != ' ' && *cp != '=' && *cp != '\n' && *cp != '\0')
			cp++;
		if (*cp != '=')  {
			n++;
			break;
		}
		len = cp - kp;
		temp[s].key = (char *) malloc((len+1) * sizeof (char));
		if (temp[s].key == NULL) {
			temp[s].val = NULL;
			PMI_Free_keyvals(temp, s);
			return PMI_FAIL;
		}
		strncpy(temp[s].key, kp, len);
		temp[s].key[len] = '\0';
		if (!IsPmiKey(temp[s].key)) {
			free(temp[s].key);
			temp[s].key = NULL;
			break;
		}
		vp = ++cp;
		while (*cp != ' ' && *cp != '\n' && *cp != '\0')
			cp++;
		len = cp - vp + 1;
		temp[s].val = (char *) malloc((len+1) * sizeof (char));
		if (temp[s].val == NULL) {
			PMI_Free_keyvals(temp, s+1);
			return PMI_FAIL;
		}
		strncpy(temp[s].val, vp, len);
		temp[s].val[len] = '\0';
		s++;
		i++;
		cp = args[i];

	}

	if (s == 0) {
		free(temp);
		temp = NULL;
	}
	*keyvalp = temp;
	*num_parsed = n;
	*size = s;

	return PMI_SUCCESS;
}
