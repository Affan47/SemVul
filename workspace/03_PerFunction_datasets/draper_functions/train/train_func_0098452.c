getCubeDecisionOrdering(int aiOrder[3],
                        float arDouble[4], float aarOutput[2][NUM_ROLLOUT_OUTPUTS], const cubeinfo * pci)
{

    cubedecision cd;


    cd = FindBestCubeDecision(arDouble, aarOutput, pci);

    switch (cd) {

    case DOUBLE_TAKE:
    case DOUBLE_BEAVER:
    case REDOUBLE_TAKE:


        aiOrder[0] = OUTPUT_TAKE;
        aiOrder[1] = OUTPUT_DROP;
        aiOrder[2] = OUTPUT_NODOUBLE;

        break;

    case DOUBLE_PASS:
    case REDOUBLE_PASS:


        aiOrder[0] = OUTPUT_DROP;
        aiOrder[1] = OUTPUT_TAKE;
        aiOrder[2] = OUTPUT_NODOUBLE;

        break;

    case NODOUBLE_TAKE:
    case NODOUBLE_BEAVER:
    case TOOGOOD_TAKE:
    case NO_REDOUBLE_TAKE:
    case NO_REDOUBLE_BEAVER:
    case TOOGOODRE_TAKE:
    case NODOUBLE_DEADCUBE:
    case NO_REDOUBLE_DEADCUBE:
    case OPTIONAL_DOUBLE_BEAVER:
    case OPTIONAL_DOUBLE_TAKE:
    case OPTIONAL_REDOUBLE_TAKE:


        aiOrder[0] = OUTPUT_NODOUBLE;
        aiOrder[1] = OUTPUT_DROP;
        aiOrder[2] = OUTPUT_TAKE;

        break;

    case TOOGOOD_PASS:
    case TOOGOODRE_PASS:
    case OPTIONAL_DOUBLE_PASS:
    case OPTIONAL_REDOUBLE_PASS:


        aiOrder[0] = OUTPUT_NODOUBLE;
        aiOrder[1] = OUTPUT_TAKE;
        aiOrder[2] = OUTPUT_DROP;

        break;

    default:

        g_assert_not_reached();

    }

}
