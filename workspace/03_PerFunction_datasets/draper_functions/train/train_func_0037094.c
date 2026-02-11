PrintSong()


{
    for(int j = 0; j < numStreams; j++)
    {
        cout << "\n\nStream " << j << ":\n";

        for(int i = 0; i < song[j].size(); i++)
        {
            cout << song[j][i].note << "\t"
                 << song[j][i].octave << "\t"
                 << song[j][i].duration
                 << ((song[j][i].note == REST) ? "\n" : "")
                 << "\n";
        }
    }
}
