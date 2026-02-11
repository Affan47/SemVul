TXT_DrawString(const char *s)
{
    int x, y;
    int x1;
    const char *p;

    TXT_GetXY(&x, &y);

    if (VALID_Y(y))
    {
        x1 = x;

        for (p = s; *p != '\0'; ++p)
        {
            if (VALID_X(x1))
            {
                TXT_GotoXY(x1, y);
                TXT_PutChar(*p);
            }

            x1 += 1;
        }
    }

    TXT_GotoXY(x + strlen(s), y);
}
