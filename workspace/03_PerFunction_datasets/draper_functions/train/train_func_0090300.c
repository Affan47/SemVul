answerQuery(Query *query)
{

    if (_by_group) {
        servicegroup *sgroup = servicegroup_list;
        servicebygroup sg;
        while (sgroup) {
            sg._servicegroup = sgroup;
            servicesmember *mem = sgroup->members;
            while (mem) {
                memcpy(&sg._service, mem->service_ptr, sizeof(service));
                if (!query->processDataset(&sg))
                    break;
                mem = mem->next;
            }
            sgroup = sgroup->next;
        }
        return;
    }


    else if (_by_hostgroup)
    {
        hostgroup *hgroup = hostgroup_list;
        servicebyhostgroup shg;
        while (hgroup) {
            shg._hostgroup = hgroup;
            hostsmember *mem = hgroup->members;
            while (mem) {
                host *hst = mem->host_ptr;
                servicesmember *smem = hst->services;
                while (smem) {
                    service *svc = smem->service_ptr;
                    memcpy(&shg._service, svc, sizeof(service));
                    if (!query->processDataset(&shg))
                        break;
                    smem = smem->next;
                }
                mem = mem->next;
            }
            hgroup = hgroup->next;
        }
        return;
    }


    char *host_name = (char *)query->findIndexFilter("host_name");
    if (host_name) {
        host *host = find_host(host_name);
        if (host) {
            servicesmember *mem = host->services;
            while (mem) {
                if (!query->processDataset(mem->service_ptr))
                    break;
                mem = mem->next;
            }
        }
        return;
    }


    servicegroup *sgroup = (servicegroup *)query->findIndexFilter("groups");
    if (sgroup) {
        servicesmember *mem = sgroup->members;
        while (mem) {
            if (!query->processDataset(mem->service_ptr))
                break;
            mem = mem->next;
        }
        return;
    }


    hostgroup *hgroup = (hostgroup *)query->findIndexFilter("host_groups");
    if (hgroup) {
        hostsmember *mem = hgroup->members;
        while (mem) {
            host *host = mem->host_ptr;
            servicesmember *smem = host->services;
            while (smem) {
                if (!query->processDataset(smem->service_ptr))
                    break;
                smem = smem->next;
            }
            mem = mem->next;
        }
        return;
    }


    service *svc = service_list;
    while (svc) {
        if (!query->processDataset(svc))
            break;
        svc = svc->next;
    }
}
