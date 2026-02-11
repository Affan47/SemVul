createShareButton(SketchAreaWidget *parent) {
	SketchToolButton *shareButton = new SketchToolButton("Share",parent, m_shareOnlineAct);
	shareButton->setText(tr("Share"));
    shareButton->setObjectName("shareProjectButton");
    shareButton->setEnabledIcon();
    return shareButton;
}
