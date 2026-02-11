command_blogs_getList(flickcurl* fc, int argc, char *argv[])
{
  flickcurl_blog** blogs = NULL;

  blogs = flickcurl_blogs_getList(fc);
  if(blogs) {
    int i;

    for(i = 0; blogs[i]; i++) {
      fprintf(stdout,
              "Blog %d) id %s  name '%s'  needs password '%d'  url '%s'\n",
              i,
              blogs[i]->id, blogs[i]->name, blogs[i]->needs_password,
              blogs[i]->url);
    }

    flickcurl_free_blogs(blogs);
  }
  return (blogs == NULL);
}
