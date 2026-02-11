setupPage()
{
   ClientList->addItem("Client list");
   ClientList->addItems(m_console->client_list);
   connect(ClientList, SIGNAL(currentIndexChanged(int)), this, SLOT(setClient()));
   connect(JobList, SIGNAL(currentIndexChanged(int)), this, SLOT(setJob()));
   connect(FileList, SIGNAL(itemClicked(QTableWidgetItem*)),
           this, SLOT(clearVersions(QTableWidgetItem *)));
   connect(FileList, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
           this, SLOT(showInfoForFile(QTableWidgetItem *)));
   connect(LocationBp, SIGNAL(pressed()), this, SLOT(applyLocation()));
   connect(MergeChk, SIGNAL(clicked()), this, SLOT(setJob()));
   connect(ClearBp, SIGNAL(clicked()), this, SLOT(clearRestoreList()));
   connect(RestoreBp, SIGNAL(clicked()), this, SLOT(runRestore()));
   connect(FilterBp, SIGNAL(clicked()), this, SLOT(refreshView()));
   m_populated = true;
}
