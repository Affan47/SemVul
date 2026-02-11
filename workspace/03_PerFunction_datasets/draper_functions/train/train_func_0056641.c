onDataUpdated(QVariantMap map)
{
    if (map["command"] == "userdata" && map["id"] == d->mID) {
        d->mFirstName = map["first_name"].toString();
        d->mLastName = map["last_name"].toString();
        d->mPicture = map["picture"].toString();
        d->mHomeTown = map["hometown"].toString();
        d->mLocation = map["location"].toString();
        d->mCoverOffset = map["cover_offset"].toInt();

        this->requestStatusMessage();

        QUrl url (map["cover"].toString());
        QNetworkReply *reply = d->mNtManager->get(QNetworkRequest(url));

        connect(reply, SIGNAL(finished()), this, SLOT(onCoverReady()));

        setLabelName(d->mID);
        QString buttonLabel = "Write on " + d->mFirstName + "'s Wall";
        QString buttonLabel2 = d->mFirstName + "'s Feed";
        d->mWallPostButton->setLabel(buttonLabel);
        d->mFeedButton->setLabel(buttonLabel2);
    }
}
