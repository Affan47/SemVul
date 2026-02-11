print_attrs(key_cmd *cmd) {
    attr_t *attr;
    char *sep = "";

    if (cmd == NULL)
	return;

    if ((cmd->attr_bits & BIT_ATTR_NOEXEC) > 0) {
	lprintf("%snoexec", sep);
	sep = ",";
    }
    if ((cmd->attr_bits & BIT_ATTR_GRABBED) > 0) {
	lprintf("%sgrabbed", sep);
	sep = ",";
    }
    if ((cmd->attr_bits & BIT_ATTR_UNGRABBED) > 0) {
	lprintf("%sungrabbed", sep);
	sep = ",";
    }
    if ((cmd->attr_bits & BIT_ATTR_NOT) > 0) {
	lprintf("%snot", sep);
	sep = ",";
    }
    if ((cmd->attr_bits & BIT_ATTR_ALL) > 0) {
	lprintf("%sall", sep);
	sep = ",";
    }
    if ((cmd->attr_bits & BIT_ATTR_ANY) > 0) {
	lprintf("%sany", sep);
	sep = ",";
    }

    attr = cmd->attrs;
    while (attr != NULL) {
	char *str = "";
	char opt[32] = { '\0' };
	switch (attr->type) {
	    case ATTR_EXEC:
		str = "exec";
		break;
	    case ATTR_GRAB:
		str = "grab";
		break;
	    case ATTR_UNGRAB:
		str = "ungrab";
		break;
	    case ATTR_IGNREL:
		str = "ignrel";
		break;
	    case ATTR_RCVREL:
		str = "rcvrel";
		break;
	    case ATTR_ALLREL:
		str = "allrel";
		break;
	    case ATTR_KEY:
		snprintf(opt, 32, "key(%i)", (int)(attr->opt));
		break;
	    case ATTR_REL:
		snprintf(opt, 32, "rel(%i)", (int)(attr->opt));
		break;
	    case ATTR_REP:
		snprintf(opt, 32, "rep(%i)", (int)(attr->opt));
		break;
	    case ATTR_LEDON:
		snprintf(opt, 32, "ledon(%i)", (int)(attr->opt));
		break;
	    case ATTR_LEDOFF:
		snprintf(opt, 32, "ledoff(%i)", (int)(attr->opt));
		break;
	    default:
		str = "unknown";
		break;
	}
	lprintf("%s%s%s", sep, str, opt);
	attr = attr->next;
	sep = ",";
    }
}
