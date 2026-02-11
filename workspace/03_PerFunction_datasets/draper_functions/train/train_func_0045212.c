CullToParameters(
tSTREntry *data,
const lListElem *sep
) {
   lList *usage_weight_list;
   lListElem *ep;
   double cpu_w, io_w, mem_w;

   DENTER(GUI_LAYER, "CullToParameters");

   usage_weight_list = lGetList(sep, SC_usage_weight_list);

   ep = lGetElemStr(usage_weight_list, UA_name, USAGE_ATTR_CPU);
   if (ep) {

      cpu_w = floor(lGetDouble(ep, UA_value)*1000 + 0.5);
      data->cpu_weight = (int)cpu_w;
   }
   else
      data->cpu_weight = 0;

   ep = lGetElemStr(usage_weight_list, UA_name, USAGE_ATTR_MEM);
   if (ep) {

      mem_w = floor(lGetDouble(ep, UA_value)*1000 + 0.5);
      data->mem_weight = (int)mem_w;
   }
   else
      data->mem_weight = 0;

   ep = lGetElemStr(usage_weight_list, UA_name, USAGE_ATTR_IO);
   if (ep) {

      io_w = floor(lGetDouble(ep, UA_value)*1000 + 0.5);
      data->io_weight = (int)io_w;
   }
   else
      data->io_weight = 0;

   DPRINTF(("cpu_weight: %d, mem_weight: %d, io_weight: %d\n",
         data->cpu_weight, data->mem_weight, data->io_weight));

   if ((data->cpu_weight+data->io_weight+data->mem_weight) != 1000) {
      data->cpu_weight = 333;
      data->mem_weight = 333;
      data->io_weight = 334;
   }


   UsageWeightData[0].weight = data->cpu_weight;
   UsageWeightData[1].weight = data->mem_weight;
   UsageWeightData[2].weight = data->io_weight;

   data->compensation_factor = lGetDouble(sep, SC_compensation_factor);

   data->halftime = lGetUlong(sep, SC_halftime);
   if ((data->halftime/24) > 0 && (data->halftime % 24) == 0) {
      data->halftime /= 24;
      XmtChooserSetState(st_halflife_unit, 1, False);
   }

   data->halflife_decay_list = sge_strdup(data->halflife_decay_list,
                                    lGetString(sep, SC_halflife_decay_list));

   DEXIT;
}
