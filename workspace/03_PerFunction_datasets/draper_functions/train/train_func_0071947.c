outputFrame(long sampleNumber, int frameWidth, int frameHeight, int fps)


{
    Image frame(frameWidth, frameHeight, 0);
    Turtle* turtles = new Turtle[numChannels];
    int numSamples;

    for (int i=0; i < numChannels; i++)
    {
        turtles[i] = Turtle(&frame, 0x0088FF);
        turtles[i].MoveTo(0, frameHeight/numChannels*(i+1/2.0));
    }

    turtles[0].SetColor(0x00FF00);

    numSamples = sampleRate*256/44100;


    for (int j=0; j<numChannels; j++)
       turtles[j].MoveTo(0, frameHeight/numChannels*(j+1/2.0+wavData[j][sampleNumber]/2));

    for (int i=1; i<numSamples; i++)
        for (int j=0; j<numChannels; j++)
           turtles[j].LineTo(i*frameWidth/numSamples,
                             frameHeight/numChannels*(j+1/2.0+wavData[j][sampleNumber+i]/2));


    frame.Save(Utility::FindNextUntitledDocument(fileName.substr(fileName.find_last_of("/")+1,
               fileName.length()-fileName.find_last_of("/")-5).c_str(), ".bmp", Utility::NumDigits(fps*songLength)));


    delete[] turtles;
    turtles = NULL;
}
