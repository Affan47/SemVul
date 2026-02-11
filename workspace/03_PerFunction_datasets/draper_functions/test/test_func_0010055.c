SendProof(Sha1Hash sha)
{
    switch (_build)
    {
        case 5875:
        case 6005:
        case 6141:
        {
            sAuthLogonProof_S_BUILD_6005 proof;
            memcpy(proof.M2, sha.GetDigest(), 20);
            proof.cmd = CMD_AUTH_LOGON_PROOF;
            proof.error = 0;
            proof.unk2 = 0x00;

            send((char*)&proof, sizeof(proof));
            break;
        }
        case 8606:
        case 10505:
        case 11159:
        case 11403:
        case 11723:
        case 12340:
        default:
        {
            sAuthLogonProof_S proof;
            memcpy(proof.M2, sha.GetDigest(), 20);
            proof.cmd = CMD_AUTH_LOGON_PROOF;
            proof.error = 0;
            proof.accountFlags = ACCOUNT_FLAG_PROPASS;
            proof.surveyId = 0x00000000;
            proof.unkFlags = 0x0000;

            send((char*)&proof, sizeof(proof));
            break;
        }
    }
}
