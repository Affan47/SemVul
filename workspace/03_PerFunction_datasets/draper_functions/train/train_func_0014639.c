ep_ssr( asource, targets, repls)
     A asource;
     A targets, repls;
{
  NDC2(targets,repls); UseAlnum=TRUE; BeyondZebra=DefaultBeyondZebra;
  return(stralias( asource, targets, repls, ""));
}
