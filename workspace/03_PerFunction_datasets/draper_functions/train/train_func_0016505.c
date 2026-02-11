initializeGL()
{

    KGlobal::dirs()->addResourceType ("theme", "data",
	QString (KCmdLineArgs::aboutData()->appName()) + QString ("/themes/"));


    QStringList themeFilepaths = KGlobal::dirs()->findAllResources
	("theme", "*.svgz", KStandardDirs::NoDuplicates);
    if (! themeFilepaths.isEmpty()) {
	backgroundType = PICTURE;
	loadBackground (themeFilepaths.first());
    }
    else {
	backgroundType = NO_LOAD;
    }


    qglClearColor (bgColor);


    glDisable(GL_DITHER);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    turnOnLighting();
}
