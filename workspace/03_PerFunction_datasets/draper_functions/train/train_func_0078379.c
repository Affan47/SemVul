AllocateMemory()
{
    image = new Pixel*[width];

    if (showBar)
        cout << "Allocating Memory...\n";


    for (int i=0; i<width; i++)
    {
        if (showBar)
            Utility::Bar(cout, i, width);
        image[i] = new Pixel[height];
    }

    if (showBar)
    {
        Utility::Bar(cout, width, width);
        cout << endl;
    }
}
