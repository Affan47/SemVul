setCdata(const std::string& cdata)
   {
      if(getType() == Node::xml_nt_cdata)
      {
         mCdata = cdata;
      }
      else
      {
         cppdom::NodeList nl = getChildrenPred( cppdom::IsNodeTypePredicate( Node::xml_nt_cdata ));
         if(!nl.empty())
         {
            (*(nl.begin()))->setCdata(cdata);
         }
         else
         {
            cppdom::NodePtr new_cdata(new cppdom::Node("cdata", getContext()));
            new_cdata->setType(Node::xml_nt_cdata);
            new_cdata->setCdata(cdata);
            addChild(new_cdata);
         }
      }
   }
