CT_Drawer(void)
{
    int i;
    int x;
    patch_t *patch;

    if (chatmodeon)
    {
        x = 25;
        for (i = 0; i < msgptr[consoleplayer]; i++)
        {
            if (chat_msg[consoleplayer][i] < 33)
            {
                x += 6;
            }
            else
            {
                patch = W_CacheLumpNum(FontABaseLump +
                                       chat_msg[consoleplayer][i] - 33,
                                       PU_CACHE);
                V_DrawPatch(x, 10, patch);
                x += patch->width;
            }
        }
        V_DrawPatch(x, 10, W_CacheLumpName("FONTA59", PU_CACHE));
        BorderTopRefresh = true;
        UpdateState |= I_MESSAGES;
    }
}
