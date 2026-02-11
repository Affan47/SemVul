ClearMatches(int k)
{
    int i, j;

    for (i = k * 4; i < 64; i += 4)
    {
        mp[i].Color = P_VERDE1;
        mp[i].Highlight = P_VERDE0;

        if (mp[i + 3].Text)
            free(mp[i + 3].Text);

        for (j = 0; j < 4; j++)
            mp[i + j].Text = NULL;
    }
}
