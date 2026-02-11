add_inc_dir(const char *src)
{
    size_t have = CHUNK(num_inc_dir);
    size_t need = CHUNK(num_inc_dir + 1);
    size_t used = (need * sizeof(char *));
    char *save;

    if (inc_dir == 0) {
	inc_dir = (char **) malloc(used);
    } else if (have != need) {
	inc_dir = (char **) realloc(inc_dir, used);
    }

    switch (num_inc_dir) {
    case 0:

    case 1:
	inc_dir[num_inc_dir++] = trim_path_sep(xstrdup(src));
	break;
    default:
	save = inc_dir[--num_inc_dir];
	inc_dir[num_inc_dir++] = trim_path_sep(xstrdup(src));
	inc_dir[num_inc_dir++] = save;
	break;
    }
}
