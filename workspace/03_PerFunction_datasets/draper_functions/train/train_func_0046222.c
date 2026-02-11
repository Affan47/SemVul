ShowAuthors(const credEntry ace[], const char *title)
{

    int i;

    outputf("%s", title);
    outputc('\n');

    for (i = 0; ace[i].Name; ++i) {
        if (!(i % 3))
            outputc('\n');
        outputf("   %-20.20s", ace[i].Name);
    }

    outputc('\n');
    outputc('\n');

}
