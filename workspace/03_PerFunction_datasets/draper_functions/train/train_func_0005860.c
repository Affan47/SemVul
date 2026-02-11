saveProfile2As()
{
    if(!clustalw::userParameters->getProfile2Empty())
    {
        profile2Viewer->saveSequences(profile2FileName, Profile2);
    }
    else
    {
        QMessageBox::information(this, "", "Load Profile 2 first.", QMessageBox::Ok);
    }
}
