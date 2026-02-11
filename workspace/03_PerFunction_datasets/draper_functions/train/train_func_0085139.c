populate()
      {
        const std::vector<ClipDescriptor*>& clips = _descriptor->getClipsByOrder();

        int counter = 0;
        for(std::vector<ClipDescriptor*>::const_iterator it=clips.begin();
            it!=clips.end();
            ++it, ++counter) {
            const std::string &name =  (*it)->getName();

            ClipInstance* instance = newClipInstance(this, *it, counter);
            if(!instance) return kOfxStatFailed;

            _clips[name] = instance;
          }

        const std::list<Param::Descriptor*>& map = _descriptor->getParamList();

        std::map<std::string,std::vector<Param::Instance*> > parameters;
        std::map<std::string, Param::Instance*> groups;

        for(std::list<Param::Descriptor*>::const_iterator it=map.begin();
            it!=map.end();
            ++it) {
            Param::Descriptor* descriptor = (*it);

            if(!descriptor) return kOfxStatErrValue;


            std::string name = descriptor->getName();


            Param::Instance* instance = newParam(name,*descriptor);
            if(!instance) return kOfxStatFailed;


            OfxStatus st = addParam(name,instance);
            if(st != kOfxStatOK) return st;

            std::string parent = instance->getParentName();

            if(parent!="")
              parameters[parent].push_back(instance);

            if(instance->getType()==kOfxParamTypeGroup){
              groups[instance->getName()]=instance;
            }
          }


        for(std::map<std::string, Param::Instance*>::iterator it=groups.begin();
            it!=groups.end();
            ++it) {

            Param::GroupInstance* group = dynamic_cast<Param::GroupInstance*>(it->second);


            if(group){

              std::map<std::string,std::vector<Param::Instance*> >::iterator it2 = parameters.find(group->getName());
              if(it2!=parameters.end()){

                group->setChildren(it2->second);
              }
            }
          }

        return kOfxStatOK;
      }
