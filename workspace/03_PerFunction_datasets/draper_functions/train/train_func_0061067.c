print_artist(struct artist_browse* a)
{
    wrapper_wprintf(L"\nName: %s\n"
           "Genres: %s\n"
           "Years active: %s\n"
           "%d albums:\n",
           a->name, a->genres, a->years_active, a->num_albums);
    for (struct album_browse* al = a->albums; al; al = al->next)
        wrapper_wprintf(L" %s (%d)\n", al->name, al->year);
}
