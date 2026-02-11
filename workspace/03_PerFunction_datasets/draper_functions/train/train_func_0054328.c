gm_read_setup_file(std::map<std::string, std::string>& setup, bool export_env)
{
    char buffer[1024*16];
    char buffer2[1024*16];
    const char* path;
    path = getenv("GM_TOP");
    if (path == NULL) {
        path = DEFAULT_GM_TOP;
    }

    sprintf(buffer, "%s/%s",path, SETUP_FILE);
    FILE* setup_file_p = fopen(buffer, "r");
    if (setup_file_p == NULL) {
        return false;
    }


    while (fgets(buffer, 16*1024, setup_file_p) != NULL)
    {

        char* key_begin = buffer;
        if (!skip_whitespace(key_begin)) {
            continue;
        }

        if ((*key_begin == '#') || (*key_begin == '!'))
            continue;

        if ((*key_begin == ':') || (*key_begin == '='))
            continue;

        char* ptr = key_begin;
        char* val_begin;


        char last_char = find_end_of_key(ptr);
        std::string Key(key_begin);


        char* env_val = getenv(key_begin);
        if (env_val != NULL) {
            std::string  Val(env_val);
            setup[Key] = Val;
            continue;
        }

        if (last_char == '\n') {
            goto case_empty_value;
        } else if (last_char == ' ') {
            if (skip_whitespace(ptr) == false)
                goto case_empty_value;

            last_char = *ptr;
            ptr++;
        }

        if (last_char == ':') {
            if (*ptr == '=') ptr++;
            last_char = '=';
        }

        if (last_char != '=') {
            continue;
        }

        if (skip_whitespace(ptr) == false) {
            goto case_empty_value;
        }
        val_begin = ptr;


        if (create_value_expand_variables(setup, val_begin, buffer2)) {
            std::string  Val(buffer2);
            setup[Key] = Val;
            if (export_env) {
                setenv(key_begin, buffer2, 0);
            }
        }

        continue;

        case_empty_value:
            std::string  Val("");
            setup[Key] = Val;
            if (export_env) {
                setenv(key_begin, "", 0);
            }
            continue;
    }

    fclose(setup_file_p);
    return true;
}
