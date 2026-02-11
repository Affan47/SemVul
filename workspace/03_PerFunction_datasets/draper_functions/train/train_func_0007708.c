FreeMenuStuff(void)
{
    D(bug("Freeing logos...\n"));


    if (menu_music && music_playing)
        StopMenuMusic();

    if (logos) {
        FreeAnimObj(logos);
        logos = NULL;
    }

    if (symbols) {
        FreeAnimObj(symbols);
        symbols = NULL;
    }

    D(bug("Freeing background picture...\n"));

    if (back) {
        free(back);
        back = NULL;
    }

    D(bug("Freeing main bitmap...\n"));

    free(main_bitmap);

    D(bug("Freeing fonts...\n"));
    FreeMenuFonts();

    D(bug("Freeing sounds...\n"));
    LiberaSuoniMenu();

    D(bug("Begin: FreeGraphics()!\n"));
    FreeGraphics();
    D(bug("End: FreeGraphics()!\n"));

    if (music) {
        FreeSound(music);
        music = NULL;
    }
}
