operator==(const Attendee &attendee) const
{
    return
        d->mUid == attendee.d->mUid &&
        d->mRSVP == attendee.d->mRSVP &&
        d->mRole == attendee.d->mRole &&
        d->mStatus == attendee.d->mStatus &&
        d->mDelegate == attendee.d->mDelegate &&
        d->mDelegator == attendee.d->mDelegator &&
        (const Person &)*this == (const Person &)attendee;
}
