URL_dispose(URL url)
{
  if (url) {
    dispose(url->full);
    dispose(url->proto);
    dispose(url->user);
    dispose(url->password);
    dispose(url->machine);
    dispose(url->port);
    dispose(url->path);
    dispose(url->query);
    dispose(url->fragment);
    dispose(url);
  }
}
