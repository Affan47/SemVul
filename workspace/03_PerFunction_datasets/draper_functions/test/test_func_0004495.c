addScrolledContainerPage(
				      const QString &title,
				      Qt::Alignment childAlignment,
				      Qt::Alignment innerAlignment)
{
  if (!mPageTab)
  {
    kDebug(291) << "addPage: " << "Invalid layout";
    return 0;
  }

  QFrame *const page = addEmptyPage(title);
  QVBoxLayout* const vbox = new QVBoxLayout(page);
  vbox->setSpacing(KDialog::spacingHint());
  vbox->setMargin(0);

  QScrollArea* const scrollView = new QScrollArea(page);
  scrollView->setFrameStyle(QFrame::Plain);
  vbox->addWidget(scrollView);

  K3AboutContainer* const container = new K3AboutContainer(scrollView,
    KDialog::spacingHint(), KDialog::spacingHint(), childAlignment,
    innerAlignment);
  scrollView->setWidget(container);
  return container;
}
