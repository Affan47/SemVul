set_accept_quality(negotiation_state *neg, var_rec *variant)
{
    int i;
    accept_rec *accept_recs;
    float q = 0.0f;
    int q_definite = 1;


    if (!neg->accepts) {
        if (variant->mime_type && *variant->mime_type)
            variant->definite = 0;
        return;
    }

    accept_recs = (accept_rec *) neg->accepts->elts;


    for (i = 0; i < neg->accepts->nelts; ++i) {

        accept_rec *type = &accept_recs[i];
        int prev_mime_stars;

        prev_mime_stars = variant->mime_stars;

        if (!mime_match(type, variant)) {
            continue;
        }
        else {


            if (prev_mime_stars == variant->mime_stars) {
                continue;
            }
        }


        if (!neg->dont_fiddle_headers && !neg->accept_q &&
            variant->mime_stars == 1) {
            q = 0.01f;
        }
        else if (!neg->dont_fiddle_headers && !neg->accept_q &&
                 variant->mime_stars == 2) {
            q = 0.02f;
        }
        else {
            q = type->quality;
        }

        q_definite = (variant->mime_stars == 3);
    }
    variant->mime_type_quality = q;
    variant->definite = variant->definite && q_definite;

}
