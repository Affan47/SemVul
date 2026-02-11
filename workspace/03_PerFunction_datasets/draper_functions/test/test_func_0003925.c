createToolBars()
{
	GraphicsSceneMainWindow::createToolBars();

	mBuildToolBar = addToolBar(tr("&Build"));
	mBuildToolBar->setObjectName("BuildToolBar");


	mTargetsComboBox = new QComboBox( this );
    mTargetsComboBox->setToolTip(tr("Target architecture"));
    mTargetsComboBox->setStatusTip(tr("Choose the exported plug-in architecture"));
	connect( mTargetsComboBox , SIGNAL(currentIndexChanged(int)) , this , SLOT(targetArchitectureChanged(int)) );
	mBuildToolBar->addWidget( mTargetsComboBox );

	mOptionsComboBox = new QComboBox( this );
    mOptionsComboBox->setToolTip(tr("Build options"));
    mOptionsComboBox->setStatusTip(tr("Build options used for $OPTIONS by binary build scripts"));
	connect( mOptionsComboBox , SIGNAL(currentIndexChanged(int)) , this , SLOT(buildOptionsChanged(int)) );
	mBuildToolBar->addWidget( mOptionsComboBox );
}
