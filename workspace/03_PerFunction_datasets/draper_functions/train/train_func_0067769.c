operator/ (const ETCL_Literal_Constraint & rhs)
{
  Literal_Type widest_type = this->widest_type (rhs);

  switch (widest_type)
    {
    case ACE_ETCL_DOUBLE:
      {
        if (ACE::is_equal ((ACE_CDR::Double) rhs, 0.0))
          return ETCL_Literal_Constraint ((ACE_CDR::Double) 0.0);

        ACE_CDR::Double result = (ACE_CDR::Double) *this / (ACE_CDR::Double) rhs;
        return ETCL_Literal_Constraint ((ACE_CDR::Double) result);
      }
    case ACE_ETCL_INTEGER:
    case ACE_ETCL_SIGNED:
      {
        if ((ACE_CDR::Long) rhs == 0)
          return ETCL_Literal_Constraint ((ACE_CDR::Long) 0);

        ACE_CDR::Long result = (ACE_CDR::Long) *this / (ACE_CDR::Long) rhs;
        return ETCL_Literal_Constraint ((ACE_CDR::Long) result);
      }
    case ACE_ETCL_UNSIGNED:
      {
        if ((ACE_CDR::ULong) rhs == 0)
          return ETCL_Literal_Constraint ((ACE_CDR::ULong) 0);

        ACE_CDR::ULong result = (ACE_CDR::ULong) *this / (ACE_CDR::ULong) rhs;
        return ETCL_Literal_Constraint ((ACE_CDR::ULong) result);
      }
    default:
      return ETCL_Literal_Constraint ((ACE_CDR::Long) 0);
    }
}
