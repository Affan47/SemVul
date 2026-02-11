ShouldAnnounce() const
{
    return se_shuffleSpamMessagesPerRound <= 0 || numberShuffles_ < se_shuffleSpamMessagesPerRound;
}
