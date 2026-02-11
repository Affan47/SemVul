setUpCombo()
{
    QGridLayout *grid = new QGridLayout;
    useProfile1SS = new QComboBox;
    useProfile1SS->addItem("Yes");
    useProfile1SS->addItem("No");
    if(clustalw::userParameters->getUseSS1())
    {
        useProfile1SS->setCurrentIndex(0);
    }
    else
    {
        useProfile1SS->setCurrentIndex(1);
    }

    useProfile2SS = new QComboBox;
    useProfile2SS->addItem("Yes");
    useProfile2SS->addItem("No");
    if(clustalw::userParameters->getUseSS2())
    {
        useProfile2SS->setCurrentIndex(0);
    }
    else
    {
        useProfile2SS->setCurrentIndex(1);
    }

    useProfile1SSLabel = new QLabel("Use profile 1 secondary structure / penalty mask");
    useProfile2SSLabel = new QLabel("Use profile 2 secondary structure / penalty mask");

    grid->addWidget(useProfile1SSLabel, 0, 0);
    grid->addWidget(useProfile1SS, 0, 1);
    grid->addWidget(useProfile2SSLabel, 1, 0);
    grid->addWidget(useProfile2SS, 1, 1);

    ssGridBox->setLayout(grid);

}
