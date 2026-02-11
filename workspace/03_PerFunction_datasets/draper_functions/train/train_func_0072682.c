ChallengeHash(u_char PeerChallenge[16], u_char *rchallenge,
	      char *username, u_char Challenge[8])

{
    SHA1_CTX	sha1Context;
    u_char	sha1Hash[SHA1_SIGNATURE_SIZE];
    char	*user;


    if ((user = strrchr(username, '\\')) != NULL)
	++user;
    else
	user = username;

    SHA1_Init(&sha1Context);
    SHA1_Update(&sha1Context, PeerChallenge, 16);
    SHA1_Update(&sha1Context, rchallenge, 16);
    SHA1_Update(&sha1Context, (unsigned char *)user, strlen(user));
    SHA1_Final(sha1Hash, &sha1Context);

    BCOPY(sha1Hash, Challenge, 8);
}
