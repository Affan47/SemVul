parseCommit(RCommit& commit) {

    while(parseCommitEntry(commit));

    return !commit.files.empty();
}
