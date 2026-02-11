init_style()
{
        if(force->newton_pair == 0)
                error->all(FLERR,"Pair style meam/spline requires newton pair on");


        int irequest_full = neighbor->request(this);
        neighbor->requests[irequest_full]->id = 1;
        neighbor->requests[irequest_full]->half = 0;
        neighbor->requests[irequest_full]->full = 1;
        int irequest_half = neighbor->request(this);
        neighbor->requests[irequest_half]->id = 2;
        neighbor->requests[irequest_half]->half = 0;
        neighbor->requests[irequest_half]->half_from_full = 1;
        neighbor->requests[irequest_half]->otherlist = irequest_full;
}
