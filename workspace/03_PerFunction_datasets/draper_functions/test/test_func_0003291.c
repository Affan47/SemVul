gva_music_button_set_game (GvaMusicButton *music_button,
                           const gchar *game)
{
        g_return_if_fail (GVA_IS_MUSIC_BUTTON (music_button));

        if (game != NULL)
                game = g_intern_string (game);

        music_button->priv->game = game;

#ifdef HAVE_GSTREAMER
        music_button_setup_element (music_button);
#endif

        g_object_notify (G_OBJECT (music_button), "game");
}
