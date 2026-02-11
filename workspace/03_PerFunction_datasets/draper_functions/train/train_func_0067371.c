ensureSeekGraph() {
  if (global.skgraph2==NULL) {
    global.skgraph2=new SeekGraph2();
    global.skgraph2->show();
    global.ebook->addPage(global.skgraph2->widget,_("Seek Graph"),-3);
    global.skgraph2->setNotebook(global.ebook,-3);
  }
}
