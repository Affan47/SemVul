setModel (char *answer)
{
    if (answer == NULL) {
        conf.model = MODEL_DEFAULT;
    } else if (strstr(answer,STR_MOTOROLA)) {
        conf.model = MODEL_MOTOROLA;
    } else if (strstr(answer,STR_SE)) {
        conf.model = MODEL_SE;
    } else if (strstr(answer,STR_SAGEM)) {
        conf.model = MODEL_SAGEM;
    } else if (strstr(answer,STR_SIEMENS)) {
        conf.model = MODEL_SIEMENS;
    } else {
        conf.model = MODEL_DEFAULT;
    }
}
