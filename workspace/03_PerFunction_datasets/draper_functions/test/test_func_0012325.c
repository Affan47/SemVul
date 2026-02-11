_vacm_choose_best( struct vacm_accessEntry *current,
                   struct vacm_accessEntry *candidate)
{


    if (( !current ) ||


        (  current->securityModel == SNMP_SEC_MODEL_ANY &&
         candidate->securityModel != SNMP_SEC_MODEL_ANY ) ||


        (  current->contextMatch  == CONTEXT_MATCH_PREFIX &&
         candidate->contextMatch  == CONTEXT_MATCH_EXACT ) ||


        (  current->contextMatch  == CONTEXT_MATCH_PREFIX &&
           current->contextPrefix[0] < candidate->contextPrefix[0] ) ||


        (  current->securityLevel < candidate->securityLevel )) {

        return candidate;
    }

    return current;
}
