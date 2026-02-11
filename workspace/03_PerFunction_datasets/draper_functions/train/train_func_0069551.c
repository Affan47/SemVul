find_skill_by_name(object *who, const char *name) {
    object *skill = NULL, *skills[NUM_SKILLS], *skill_tools[NUM_SKILLS];
    const char *skill_names[NUM_SKILLS];
    char *ourname=NULL;
    int num_names, highest_level_skill=0, i;

    if (!name)
        return NULL;


    if (!strchr(name, ',')) {
        skill_names[0] = name;
        skill_tools[0] = NULL;
        skills[0] = NULL;
        num_names = 1;
    } else {

        char *lasts;
        ourname = strdup(name);

        if ((skill_names[0] = strtok_r(ourname, ",", &lasts)) == NULL) {

            LOG(llevError, "find_skill_by_name: strtok_r returned null, but strchr did not?\n");
            return NULL;
        } else {
            skill_tools[0] = NULL;
            skills[0] = NULL;

            num_names=1;
            while ((skill_names[num_names] = strtok_r(NULL, ",", &lasts)) != NULL) {


                while (isspace(*skill_names[num_names]))
                    skill_names[num_names]++;
                skills[num_names] = NULL;
                skill_tools[num_names] = NULL;
                num_names++;
            }
        }


    }

    FOR_INV_PREPARE(who, tmp) {


        if (tmp->type == SKILL || tmp->type == SKILL_TOOL) {
            for (i = 0; i<num_names; i++) {
                if (!strncasecmp(skill_names[i], tmp->skill, strlen(skill_names[i])) &&
                    strlen(tmp->skill) >= strlen(skill_names[i])) {
                    if (tmp->type == SKILL) {
                        skills[i] = tmp;
                        if (!skill || tmp->level > skill->level) {
                            skill = tmp;
                            highest_level_skill=i;
                        }
                    }
                    else {


                        if (QUERY_FLAG(tmp, FLAG_APPLIED) || !skill_tools[i] ||
                            !QUERY_FLAG(skill_tools[i], FLAG_APPLIED)) {
                                skill_tools[i] = tmp;
                            }
                    }

                    break;
                }
            }
        }
    } FOR_INV_FINISH();
    free(ourname);
    return adjust_skill_tool(who, skills[highest_level_skill], skill_tools[highest_level_skill]);
}
