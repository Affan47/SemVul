parse_learn2_config(void)
{
        grlearn_configin = fopen(GR_LEARN_CONFIG_PATH, "r");
        if (grlearn_configin == NULL) {
                fprintf(stdout, "Unable to open %s: %s\n", GR_LEARN_CONFIG_PATH, strerror(errno));
                exit(EXIT_FAILURE);
        }
        grlearn2_configparse();
	fclose(grlearn_configin);
        return;
}
